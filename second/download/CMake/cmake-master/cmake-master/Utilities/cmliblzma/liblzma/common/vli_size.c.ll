; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/vli_size.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [7 x i8] c"i <= 9\00", align 1
@.str.1 = private unnamed_addr constant [80 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/vli_size.c\00", align 1
@__PRETTY_FUNCTION__.lzma_vli_size = private unnamed_addr constant [33 x i8] c"uint32_t lzma_vli_size(lzma_vli)\00", align 1

; Function Attrs: nounwind readonly uwtable
define i32 @lzma_vli_size(i64 %vli) #0 !dbg !4 {
entry:
  %retval = alloca i32, align 4
  %vli.addr = alloca i64, align 8
  %i = alloca i32, align 4
  store i64 %vli, i64* %vli.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %vli.addr, metadata !17, metadata !18), !dbg !19
  call void @llvm.dbg.declare(metadata i32* %i, metadata !20, metadata !18), !dbg !21
  store i32 0, i32* %i, align 4, !dbg !21
  %0 = load i64, i64* %vli.addr, align 8, !dbg !22
  %cmp = icmp ugt i64 %0, 9223372036854775807, !dbg !24
  br i1 %cmp, label %if.then, label %if.end, !dbg !25

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !26
  br label %return, !dbg !26

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !27

do.body:                                          ; preds = %do.cond, %if.end
  %1 = load i64, i64* %vli.addr, align 8, !dbg !28
  %shr = lshr i64 %1, 7, !dbg !28
  store i64 %shr, i64* %vli.addr, align 8, !dbg !28
  %2 = load i32, i32* %i, align 4, !dbg !30
  %inc = add i32 %2, 1, !dbg !30
  store i32 %inc, i32* %i, align 4, !dbg !30
  br label %do.cond, !dbg !31

do.cond:                                          ; preds = %do.body
  %3 = load i64, i64* %vli.addr, align 8, !dbg !32
  %cmp1 = icmp ne i64 %3, 0, !dbg !34
  br i1 %cmp1, label %do.body, label %do.end, !dbg !35

do.end:                                           ; preds = %do.cond
  %4 = load i32, i32* %i, align 4, !dbg !36
  %cmp2 = icmp ule i32 %4, 9, !dbg !36
  br i1 %cmp2, label %cond.true, label %cond.false, !dbg !36

cond.true:                                        ; preds = %do.end
  br label %cond.end, !dbg !37

cond.false:                                       ; preds = %do.end
  call void @__assert_fail(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([80 x i8], [80 x i8]* @.str.1, i32 0, i32 0), i32 29, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @__PRETTY_FUNCTION__.lzma_vli_size, i32 0, i32 0)) #3, !dbg !38
  unreachable, !dbg !38
                                                  ; No predecessors!
  br label %cond.end, !dbg !40

cond.end:                                         ; preds = %5, %cond.true
  %6 = load i32, i32* %i, align 4, !dbg !42
  store i32 %6, i32* %retval, align 4, !dbg !43
  br label %return, !dbg !43

return:                                           ; preds = %cond.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !44
  ret i32 %7, !dbg !44
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #2

attributes #0 = { nounwind readonly uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!14, !15}
!llvm.ident = !{!16}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/vli_size.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "lzma_vli_size", scope: !1, file: !1, line: 17, type: !5, isLocal: false, isDefinition: true, scopeLine: 18, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !10}
!7 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !8, line: 51, baseType: !9)
!8 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!9 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!10 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !11, line: 63, baseType: !12)
!11 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!12 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !8, line: 55, baseType: !13)
!13 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!14 = !{i32 2, !"Dwarf Version", i32 4}
!15 = !{i32 2, !"Debug Info Version", i32 3}
!16 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!17 = !DILocalVariable(name: "vli", arg: 1, scope: !4, file: !1, line: 17, type: !10)
!18 = !DIExpression()
!19 = !DILocation(line: 17, column: 24, scope: !4)
!20 = !DILocalVariable(name: "i", scope: !4, file: !1, line: 19, type: !7)
!21 = !DILocation(line: 19, column: 11, scope: !4)
!22 = !DILocation(line: 21, column: 6, scope: !23)
!23 = distinct !DILexicalBlock(scope: !4, file: !1, line: 21, column: 6)
!24 = !DILocation(line: 21, column: 10, scope: !23)
!25 = !DILocation(line: 21, column: 6, scope: !4)
!26 = !DILocation(line: 22, column: 3, scope: !23)
!27 = !DILocation(line: 24, column: 2, scope: !4)
!28 = !DILocation(line: 25, column: 7, scope: !29)
!29 = distinct !DILexicalBlock(scope: !4, file: !1, line: 24, column: 5)
!30 = !DILocation(line: 26, column: 3, scope: !29)
!31 = !DILocation(line: 27, column: 2, scope: !29)
!32 = !DILocation(line: 27, column: 11, scope: !33)
!33 = !DILexicalBlockFile(scope: !4, file: !1, discriminator: 1)
!34 = !DILocation(line: 27, column: 15, scope: !33)
!35 = !DILocation(line: 27, column: 2, scope: !33)
!36 = !DILocation(line: 29, column: 2, scope: !4)
!37 = !DILocation(line: 29, column: 2, scope: !33)
!38 = !DILocation(line: 29, column: 2, scope: !39)
!39 = !DILexicalBlockFile(scope: !4, file: !1, discriminator: 2)
!40 = !DILocation(line: 29, column: 2, scope: !41)
!41 = !DILexicalBlockFile(scope: !4, file: !1, discriminator: 3)
!42 = !DILocation(line: 30, column: 9, scope: !4)
!43 = !DILocation(line: 30, column: 2, scope: !4)
!44 = !DILocation(line: 31, column: 1, scope: !4)
