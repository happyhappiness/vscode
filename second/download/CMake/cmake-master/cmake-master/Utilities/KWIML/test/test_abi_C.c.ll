; ModuleID = '/data/download/cmake/cmake-master/Utilities/KWIML/test/test_abi_C.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%union.anon = type { i16 }

@.str = private unnamed_addr constant [47 x i8] c"C KWIML_ABI_ENDIAN_ID: expected [%d], got [%d]\00", align 1
@.str.1 = private unnamed_addr constant [10 x i8] c", PASSED\0A\00", align 1
@.str.2 = private unnamed_addr constant [10 x i8] c", FAILED\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @test_abi_C() #0 !dbg !4 {
entry:
  %retval = alloca i32, align 4
  %call = call i32 @test_abi_endian(), !dbg !13
  %tobool = icmp ne i32 %call, 0, !dbg !13
  br i1 %tobool, label %if.end, label %if.then, !dbg !15

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !16
  br label %return, !dbg !16

if.end:                                           ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !18
  br label %return, !dbg !18

return:                                           ; preds = %if.end, %if.then
  %0 = load i32, i32* %retval, align 4, !dbg !19
  ret i32 %0, !dbg !19
}

; Function Attrs: nounwind uwtable
define internal i32 @test_abi_endian() #0 !dbg !8 {
entry:
  %result = alloca i32, align 4
  %expect = alloca i32, align 4
  %x = alloca %union.anon, align 2
  call void @llvm.dbg.declare(metadata i32* %result, metadata !20, metadata !21), !dbg !22
  store i32 1, i32* %result, align 4, !dbg !22
  call void @llvm.dbg.declare(metadata i32* %expect, metadata !23, metadata !21), !dbg !25
  call void @llvm.dbg.declare(metadata %union.anon* %x, metadata !26, metadata !21), !dbg !36
  %s = bitcast %union.anon* %x to i16*, !dbg !37
  store i16 1, i16* %s, align 2, !dbg !38
  %c = bitcast %union.anon* %x to [2 x i8]*, !dbg !39
  %arrayidx = getelementptr inbounds [2 x i8], [2 x i8]* %c, i64 0, i64 0, !dbg !40
  %0 = load i8, i8* %arrayidx, align 2, !dbg !40
  %conv = zext i8 %0 to i32, !dbg !40
  %cmp = icmp eq i32 %conv, 1, !dbg !41
  %cond = select i1 %cmp, i32 1234, i32 4321, !dbg !40
  store i32 %cond, i32* %expect, align 4, !dbg !42
  %1 = load i32, i32* %expect, align 4, !dbg !43
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str, i32 0, i32 0), i32 %1, i32 1234), !dbg !44
  %2 = load i32, i32* %expect, align 4, !dbg !45
  %cmp2 = icmp eq i32 1234, %2, !dbg !47
  br i1 %cmp2, label %if.then, label %if.else, !dbg !48

if.then:                                          ; preds = %entry
  %call4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i32 0, i32 0)), !dbg !49
  br label %if.end, !dbg !51

if.else:                                          ; preds = %entry
  %call5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i32 0, i32 0)), !dbg !52
  store i32 0, i32* %result, align 4, !dbg !54
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %3 = load i32, i32* %result, align 4, !dbg !55
  ret i32 %3, !dbg !56
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @printf(i8*, ...) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!10, !11}
!llvm.ident = !{!12}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/KWIML/test/test_abi_C.c", directory: "/data/download/cmake/cmake-master/Utilities/KWIML/test")
!2 = !{}
!3 = !{!4, !8}
!4 = distinct !DISubprogram(name: "test_abi_C", scope: !1, file: !1, line: 12, type: !5, isLocal: false, isDefinition: true, scopeLine: 13, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = distinct !DISubprogram(name: "test_abi_endian", scope: !9, file: !9, line: 14, type: !5, isLocal: true, isDefinition: true, scopeLine: 15, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!9 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/KWIML/test/test_abi_endian.h", directory: "/data/download/cmake/cmake-master/Utilities/KWIML/test")
!10 = !{i32 2, !"Dwarf Version", i32 4}
!11 = !{i32 2, !"Debug Info Version", i32 3}
!12 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!13 = !DILocation(line: 14, column: 7, scope: !14)
!14 = distinct !DILexicalBlock(scope: !4, file: !1, line: 14, column: 6)
!15 = !DILocation(line: 14, column: 6, scope: !4)
!16 = !DILocation(line: 16, column: 5, scope: !17)
!17 = distinct !DILexicalBlock(scope: !14, file: !1, line: 15, column: 5)
!18 = !DILocation(line: 18, column: 3, scope: !4)
!19 = !DILocation(line: 19, column: 1, scope: !4)
!20 = !DILocalVariable(name: "result", scope: !8, file: !9, line: 16, type: !7)
!21 = !DIExpression()
!22 = !DILocation(line: 16, column: 7, scope: !8)
!23 = !DILocalVariable(name: "expect", scope: !24, file: !9, line: 19, type: !7)
!24 = distinct !DILexicalBlock(scope: !8, file: !9, line: 17, column: 3)
!25 = !DILocation(line: 19, column: 7, scope: !24)
!26 = !DILocalVariable(name: "x", scope: !24, file: !9, line: 20, type: !27)
!27 = !DICompositeType(tag: DW_TAG_union_type, scope: !8, file: !9, line: 20, size: 16, align: 16, elements: !28)
!28 = !{!29, !31}
!29 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !27, file: !9, line: 20, baseType: !30, size: 16, align: 16)
!30 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!31 = !DIDerivedType(tag: DW_TAG_member, name: "c", scope: !27, file: !9, line: 20, baseType: !32, size: 16, align: 8)
!32 = !DICompositeType(tag: DW_TAG_array_type, baseType: !33, size: 16, align: 8, elements: !34)
!33 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!34 = !{!35}
!35 = !DISubrange(count: 2)
!36 = !DILocation(line: 20, column: 54, scope: !24)
!37 = !DILocation(line: 21, column: 5, scope: !24)
!38 = !DILocation(line: 21, column: 7, scope: !24)
!39 = !DILocation(line: 22, column: 15, scope: !24)
!40 = !DILocation(line: 22, column: 13, scope: !24)
!41 = !DILocation(line: 22, column: 20, scope: !24)
!42 = !DILocation(line: 22, column: 10, scope: !24)
!43 = !DILocation(line: 25, column: 10, scope: !24)
!44 = !DILocation(line: 24, column: 3, scope: !24)
!45 = !DILocation(line: 26, column: 29, scope: !46)
!46 = distinct !DILexicalBlock(scope: !24, file: !9, line: 26, column: 6)
!47 = !DILocation(line: 26, column: 26, scope: !46)
!48 = !DILocation(line: 26, column: 6, scope: !24)
!49 = !DILocation(line: 28, column: 5, scope: !50)
!50 = distinct !DILexicalBlock(scope: !46, file: !9, line: 27, column: 5)
!51 = !DILocation(line: 29, column: 5, scope: !50)
!52 = !DILocation(line: 32, column: 5, scope: !53)
!53 = distinct !DILexicalBlock(scope: !46, file: !9, line: 31, column: 5)
!54 = !DILocation(line: 33, column: 12, scope: !53)
!55 = !DILocation(line: 40, column: 10, scope: !8)
!56 = !DILocation(line: 40, column: 3, scope: !8)
