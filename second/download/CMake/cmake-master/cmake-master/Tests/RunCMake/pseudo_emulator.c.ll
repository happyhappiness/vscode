; ModuleID = '/data/download/cmake/cmake-master/Tests/RunCMake/pseudo_emulator.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [9 x i8] c"Command:\00", align 1
@.str.1 = private unnamed_addr constant [6 x i8] c" \22%s\22\00", align 1
@.str.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main(i32 %argc, i8** %argv) #0 !dbg !4 {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %ii = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 %argc, i32* %argc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %argc.addr, metadata !14, metadata !15), !dbg !16
  store i8** %argv, i8*** %argv.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %argv.addr, metadata !17, metadata !15), !dbg !18
  call void @llvm.dbg.declare(metadata i32* %ii, metadata !19, metadata !15), !dbg !20
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str, i32 0, i32 0)), !dbg !21
  store i32 1, i32* %ii, align 4, !dbg !22
  br label %for.cond, !dbg !24

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %ii, align 4, !dbg !25
  %1 = load i32, i32* %argc.addr, align 4, !dbg !28
  %cmp = icmp slt i32 %0, %1, !dbg !29
  br i1 %cmp, label %for.body, label %for.end, !dbg !30

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %ii, align 4, !dbg !31
  %idxprom = sext i32 %2 to i64, !dbg !33
  %3 = load i8**, i8*** %argv.addr, align 8, !dbg !33
  %arrayidx = getelementptr inbounds i8*, i8** %3, i64 %idxprom, !dbg !33
  %4 = load i8*, i8** %arrayidx, align 8, !dbg !33
  %call1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i8* %4), !dbg !34
  br label %for.inc, !dbg !35

for.inc:                                          ; preds = %for.body
  %5 = load i32, i32* %ii, align 4, !dbg !36
  %inc = add nsw i32 %5, 1, !dbg !36
  store i32 %inc, i32* %ii, align 4, !dbg !36
  br label %for.cond, !dbg !38

for.end:                                          ; preds = %for.cond
  %call2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0)), !dbg !39
  ret i32 42, !dbg !40
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @printf(i8*, ...) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!11, !12}
!llvm.ident = !{!13}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Tests/RunCMake/pseudo_emulator.c", directory: "/data/download/cmake/cmake-master/Tests/RunCMake")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 3, type: !5, isLocal: false, isDefinition: true, scopeLine: 4, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !7, !8}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!11 = !{i32 2, !"Dwarf Version", i32 4}
!12 = !{i32 2, !"Debug Info Version", i32 3}
!13 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!14 = !DILocalVariable(name: "argc", arg: 1, scope: !4, file: !1, line: 3, type: !7)
!15 = !DIExpression()
!16 = !DILocation(line: 3, column: 14, scope: !4)
!17 = !DILocalVariable(name: "argv", arg: 2, scope: !4, file: !1, line: 3, type: !8)
!18 = !DILocation(line: 3, column: 26, scope: !4)
!19 = !DILocalVariable(name: "ii", scope: !4, file: !1, line: 5, type: !7)
!20 = !DILocation(line: 5, column: 7, scope: !4)
!21 = !DILocation(line: 7, column: 3, scope: !4)
!22 = !DILocation(line: 8, column: 11, scope: !23)
!23 = distinct !DILexicalBlock(scope: !4, file: !1, line: 8, column: 3)
!24 = !DILocation(line: 8, column: 8, scope: !23)
!25 = !DILocation(line: 8, column: 16, scope: !26)
!26 = !DILexicalBlockFile(scope: !27, file: !1, discriminator: 1)
!27 = distinct !DILexicalBlock(scope: !23, file: !1, line: 8, column: 3)
!28 = !DILocation(line: 8, column: 21, scope: !26)
!29 = !DILocation(line: 8, column: 19, scope: !26)
!30 = !DILocation(line: 8, column: 3, scope: !26)
!31 = !DILocation(line: 9, column: 28, scope: !32)
!32 = distinct !DILexicalBlock(scope: !27, file: !1, line: 8, column: 33)
!33 = !DILocation(line: 9, column: 23, scope: !32)
!34 = !DILocation(line: 9, column: 5, scope: !32)
!35 = !DILocation(line: 10, column: 3, scope: !32)
!36 = !DILocation(line: 8, column: 27, scope: !37)
!37 = !DILexicalBlockFile(scope: !27, file: !1, discriminator: 2)
!38 = !DILocation(line: 8, column: 3, scope: !37)
!39 = !DILocation(line: 11, column: 3, scope: !4)
!40 = !DILocation(line: 13, column: 3, scope: !4)
