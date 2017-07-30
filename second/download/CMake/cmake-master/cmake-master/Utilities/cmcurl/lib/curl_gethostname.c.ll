; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_gethostname.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @Curl_gethostname(i8* %name, i64 %namelen) #0 !dbg !4 {
entry:
  %retval = alloca i32, align 4
  %name.addr = alloca i8*, align 8
  %namelen.addr = alloca i64, align 8
  %err = alloca i32, align 4
  %dot = alloca i8*, align 8
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !16, metadata !17), !dbg !18
  store i64 %namelen, i64* %namelen.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %namelen.addr, metadata !19, metadata !17), !dbg !20
  call void @llvm.dbg.declare(metadata i32* %err, metadata !21, metadata !17), !dbg !22
  call void @llvm.dbg.declare(metadata i8** %dot, metadata !23, metadata !17), !dbg !24
  %0 = load i8*, i8** %name.addr, align 8, !dbg !25
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !25
  store i8 0, i8* %arrayidx, align 1, !dbg !26
  %1 = load i8*, i8** %name.addr, align 8, !dbg !27
  %2 = load i64, i64* %namelen.addr, align 8, !dbg !28
  %call = call i32 @gethostname(i8* %1, i64 %2) #4, !dbg !29
  store i32 %call, i32* %err, align 4, !dbg !30
  %3 = load i64, i64* %namelen.addr, align 8, !dbg !31
  %sub = sub i64 %3, 1, !dbg !32
  %4 = load i8*, i8** %name.addr, align 8, !dbg !33
  %arrayidx1 = getelementptr inbounds i8, i8* %4, i64 %sub, !dbg !33
  store i8 0, i8* %arrayidx1, align 1, !dbg !34
  %5 = load i32, i32* %err, align 4, !dbg !35
  %tobool = icmp ne i32 %5, 0, !dbg !35
  br i1 %tobool, label %if.then, label %if.end, !dbg !37

if.then:                                          ; preds = %entry
  %6 = load i32, i32* %err, align 4, !dbg !38
  store i32 %6, i32* %retval, align 4, !dbg !39
  br label %return, !dbg !39

if.end:                                           ; preds = %entry
  %7 = load i8*, i8** %name.addr, align 8, !dbg !40
  %call2 = call i8* @strchr(i8* %7, i32 46) #5, !dbg !41
  store i8* %call2, i8** %dot, align 8, !dbg !42
  %8 = load i8*, i8** %dot, align 8, !dbg !43
  %tobool3 = icmp ne i8* %8, null, !dbg !43
  br i1 %tobool3, label %if.then4, label %if.end5, !dbg !45

if.then4:                                         ; preds = %if.end
  %9 = load i8*, i8** %dot, align 8, !dbg !46
  store i8 0, i8* %9, align 1, !dbg !47
  br label %if.end5, !dbg !48

if.end5:                                          ; preds = %if.then4, %if.end
  store i32 0, i32* %retval, align 4, !dbg !49
  br label %return, !dbg !49

return:                                           ; preds = %if.end5, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !50
  ret i32 %10, !dbg !50
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare i32 @gethostname(i8*, i64) #2

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }
attributes #5 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!13, !14}
!llvm.ident = !{!15}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_gethostname.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "Curl_gethostname", scope: !1, file: !1, line: 51, type: !5, isLocal: false, isDefinition: true, scopeLine: 52, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8, !10}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!10 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !11, line: 62, baseType: !12)
!11 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!12 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!13 = !{i32 2, !"Dwarf Version", i32 4}
!14 = !{i32 2, !"Debug Info Version", i32 3}
!15 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!16 = !DILocalVariable(name: "name", arg: 1, scope: !4, file: !1, line: 51, type: !8)
!17 = !DIExpression()
!18 = !DILocation(line: 51, column: 28, scope: !4)
!19 = !DILocalVariable(name: "namelen", arg: 2, scope: !4, file: !1, line: 51, type: !10)
!20 = !DILocation(line: 51, column: 56, scope: !4)
!21 = !DILocalVariable(name: "err", scope: !4, file: !1, line: 61, type: !7)
!22 = !DILocation(line: 61, column: 7, scope: !4)
!23 = !DILocalVariable(name: "dot", scope: !4, file: !1, line: 62, type: !8)
!24 = !DILocation(line: 62, column: 9, scope: !4)
!25 = !DILocation(line: 82, column: 3, scope: !4)
!26 = !DILocation(line: 82, column: 11, scope: !4)
!27 = !DILocation(line: 83, column: 21, scope: !4)
!28 = !DILocation(line: 83, column: 27, scope: !4)
!29 = !DILocation(line: 83, column: 9, scope: !4)
!30 = !DILocation(line: 83, column: 7, scope: !4)
!31 = !DILocation(line: 87, column: 8, scope: !4)
!32 = !DILocation(line: 87, column: 16, scope: !4)
!33 = !DILocation(line: 87, column: 3, scope: !4)
!34 = !DILocation(line: 87, column: 21, scope: !4)
!35 = !DILocation(line: 89, column: 6, scope: !36)
!36 = distinct !DILexicalBlock(scope: !4, file: !1, line: 89, column: 6)
!37 = !DILocation(line: 89, column: 6, scope: !4)
!38 = !DILocation(line: 90, column: 12, scope: !36)
!39 = !DILocation(line: 90, column: 5, scope: !36)
!40 = !DILocation(line: 93, column: 16, scope: !4)
!41 = !DILocation(line: 93, column: 9, scope: !4)
!42 = !DILocation(line: 93, column: 7, scope: !4)
!43 = !DILocation(line: 94, column: 6, scope: !44)
!44 = distinct !DILexicalBlock(scope: !4, file: !1, line: 94, column: 6)
!45 = !DILocation(line: 94, column: 6, scope: !4)
!46 = !DILocation(line: 95, column: 6, scope: !44)
!47 = !DILocation(line: 95, column: 10, scope: !44)
!48 = !DILocation(line: 95, column: 5, scope: !44)
!49 = !DILocation(line: 97, column: 3, scope: !4)
!50 = !DILocation(line: 100, column: 1, scope: !4)
